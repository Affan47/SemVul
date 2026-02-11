readCgiResponseData(HttpQueue *q, MprCmd *cmd, int channel, MprBuf *buf)
{
    HttpConn    *conn;
    ssize       space, nbytes, total;
    int         err;

    conn = q->conn;
#if UNUSED
    mprAssert(!cmd->disconnected);
#endif
    mprAssert(conn->state > HTTP_STATE_BEGIN);
    mprResetBufIfEmpty(buf);
    total = 0;


    while (mprGetCmdFd(cmd, channel) >= 0 && conn->sock && conn->state > HTTP_STATE_BEGIN) {
        do {
            mprAssert(conn->state > HTTP_STATE_BEGIN);


            if ((space = mprGetBufSpace(buf)) == 0) {
                mprGrowBuf(buf, MPR_BUFSIZE);
                if ((space = mprGetBufSpace(buf)) == 0) {
                    break;
                }
            }
            mprYield(MPR_YIELD_STICKY);
            nbytes = mprReadCmd(cmd, channel, mprGetBufEnd(buf), space);
            mprResetYield();

            mprLog(7, "CGI: Read from gateway, channel %d, got %d bytes. errno %d", channel, nbytes,
                nbytes >= 0 ? 0 : mprGetOsError());
            if (nbytes < 0) {
                err = mprGetError();
                if (err == EINTR) {
                    continue;
                } else if (err == EAGAIN || err == EWOULDBLOCK) {
                    break;
                }
                mprLog(5, "CGI: Gateway read error %d for %s", err, (channel == MPR_CMD_STDOUT) ? "stdout" : "stderr");


                mprCloseCmdFd(cmd, channel);
                break;

            } else if (nbytes == 0) {


                mprLog(5, "CGI: Gateway EOF for %s, pid %d", (channel == MPR_CMD_STDOUT) ? "stdout" : "stderr", cmd->pid);


                mprCloseCmdFd(cmd, channel);
                break;

            } else {
                mprLog(5, "CGI: Gateway read %d bytes from %s", nbytes, (channel == MPR_CMD_STDOUT) ? "stdout" : "stderr");
                mprAdjustBufEnd(buf, nbytes);
                traceData(cmd, mprGetBufStart(buf), nbytes);
                mprAddNullToBuf(buf);
                total += nbytes;
            }
            conn->lastActivity = conn->http->now;
        } while ((space = mprGetBufSpace(buf)) > 0 && conn->state > HTTP_STATE_BEGIN);

        if (conn->state == HTTP_STATE_BEGIN) {
            return total;
        }
        if (mprGetBufLength(buf) == 0) {
            break;
        }
        if (processCgiData(q, cmd, channel, buf) < 0) {
            break;
        }
    }
    if (cmd->complete && conn->state > HTTP_STATE_BEGIN) {
        mprAssert(conn->tx);
        httpFinalize(conn);
    }
    return total;
}
