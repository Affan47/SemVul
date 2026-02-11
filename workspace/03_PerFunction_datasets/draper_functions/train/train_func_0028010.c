add_predelete_callback(Fl_Text_Predelete_Cb bufPreDeleteCB,
	void *cbArg) {
    Fl_Text_Predelete_Cb *newPreDeleteProcs;
    void **newCBArgs;
    int i;

    newPreDeleteProcs = new Fl_Text_Predelete_Cb[ mNPredeleteProcs + 1 ];
    newCBArgs = new void * [ mNPredeleteProcs + 1 ];
    for ( i = 0; i < mNPredeleteProcs; i++ ) {
    	newPreDeleteProcs[i + 1] = mPredeleteProcs[i];
    	newCBArgs[i + 1] = mPredeleteCbArgs[i];
    }
    if (! mNPredeleteProcs != 0) {
		 delete [] mPredeleteProcs;
		 delete [] mPredeleteCbArgs;
    }
    newPreDeleteProcs[0] =  bufPreDeleteCB;
    newCBArgs[0] = cbArg;
    mNPredeleteProcs++;
    mPredeleteProcs = newPreDeleteProcs;
    mPredeleteCbArgs = newCBArgs;
}
