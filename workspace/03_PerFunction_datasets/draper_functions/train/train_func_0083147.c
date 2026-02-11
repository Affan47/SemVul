FileSaveAll() {
    for (EModel *M = Model; M; M = M->Next) {
        if (M->GetContext() == CONTEXT_FILE) {
            EBuffer *B = (EBuffer *)M;
            if (B->Modified) {
                SwitchToModel(B);
		if (B->Save() == 0)
		    return 0;
            }
        }
	if (M->Next == Model)
	    break;
    }
    return 1;
}
