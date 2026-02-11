Scm_SysPrepareFdMap(ScmObj iomap)
{
    int *fds = NULL;
    if (SCM_PAIRP(iomap)) {
        ScmObj iop;
        int iollen = Scm_Length(iomap), i = 0;
        int *tofd, *fromfd;


        if (iollen < 0) {
            Scm_Error("proper list required for iolist, but got %S", iomap);
        }
        fds    = SCM_NEW_ATOMIC2(int *, 2 * iollen * sizeof(int) + 1);
        fds[0] = iollen;
        tofd   = fds + 1;
        fromfd = fds + 1 + iollen;
        SCM_FOR_EACH(iop, iomap) {
            ScmObj port, elt = SCM_CAR(iop);
            if (!SCM_PAIRP(elt) || !SCM_INTP(SCM_CAR(elt))
                || (!SCM_PORTP(SCM_CDR(elt)) && !SCM_INTP(SCM_CDR(elt)))) {
                Scm_Error("bad iomap specification: needs (int . int-or-port): %S", elt);
            }
            tofd[i] = SCM_INT_VALUE(SCM_CAR(elt));
            if (SCM_INTP(SCM_CDR(elt))) {
                fromfd[i] = SCM_INT_VALUE(SCM_CDR(elt));
            } else {
                port = SCM_CDAR(iop);
                fromfd[i] = Scm_PortFileNo(SCM_PORT(port));
                if (fromfd[i] < 0) {
                    Scm_Error("iolist requires a port that has associated file descriptor, but got %S",
                              SCM_CDAR(iop));
                }
                if (tofd[i] == 0 && !SCM_IPORTP(port))
                    Scm_Error("input port required to make it stdin: %S",
                              port);
                if (tofd[i] == 1 && !SCM_OPORTP(port))
                    Scm_Error("output port required to make it stdout: %S",
                              port);
                if (tofd[i] == 2 && !SCM_OPORTP(port))
                    Scm_Error("output port required to make it stderr: %S",
                              port);
            }
            i++;
        }
    }
    return fds;
}
