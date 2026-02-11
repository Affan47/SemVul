Svn(char *Options) {
    char Dir[MAXPATH] = "";
    char Command[256] = "";
    char buf[1024] = "";
    char *OnFiles = buf;
    ESvn *svn;

    if (GetDefaultDirectory(Model, Dir, sizeof(Dir)) == 0) return 0;

    strlcpy(Command, SvnCommand, sizeof(Command));
    strlcat(Command, " ", sizeof(Command));
    if (Options[0] != 0) {
        strlcat(Command, Options, sizeof(Command));
        strlcat(Command, " ", sizeof(Command));
    }

    switch (Model->GetContext()) {
        case CONTEXT_FILE:
            if (JustFileName(((EBuffer *)Model)->FileName, OnFiles, sizeof(buf)) != 0) return 0;
            break;
        case CONTEXT_SVNDIFF:
            OnFiles = strdup(SvnDiffView->OnFiles);
            break;
        case CONTEXT_SVN:
            OnFiles = ((ESvn *)Model)->MarkedAsList();
            if (!OnFiles) OnFiles = strdup(((ESvn *)Model)->OnFiles);
            break;
    }

    if (SvnView != 0) {
        SvnView->RunPipe(Dir, Command, OnFiles);
        svn = SvnView;
    } else {
        svn = new ESvn(0, &ActiveModel, Dir, Command, OnFiles);
    }
    if (OnFiles != buf) free(OnFiles);
    SwitchToModel(svn);
    return 1;
}
