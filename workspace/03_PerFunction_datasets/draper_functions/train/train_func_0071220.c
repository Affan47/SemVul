pkix_pl_socket_tracebuff(void *buf, PKIX_UInt32 nBytes) {
        PKIX_UInt32 bytesRemaining = nBytes;
        PKIX_UInt32 offset = 0;
        char *bufptr = (char *)buf;

        if (socketTraceFlag == PKIX_FALSE) return;

        pkix_pl_socket_timestamp();


        if (nBytes == 0) {
                pkix_pl_socket_linePrefix((PKIX_UInt32)buf);
                printf("\n");
        } else {
                while (bytesRemaining >= 16) {
                        pkix_pl_socket_traceLine(&bufptr[offset]);
                        bytesRemaining -= 16;
                        offset += 16;
                }
                pkix_pl_socket_tracePartialLine
                        (&bufptr[offset], bytesRemaining);
        }
}
