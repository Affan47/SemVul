stopWork(bool success = true, const string & msg = "")
{


    setSigPollAction(false);

    canSendStderr = false;

    if (success)
        writeInt(STDERR_LAST, to);
    else {
        writeInt(STDERR_ERROR, to);
        writeString(msg, to);
    }
}
