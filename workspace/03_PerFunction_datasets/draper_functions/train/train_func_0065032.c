GetWave(int const i) {
	static CWaveInfo wi={0,};

    DBG1("(i=%d)\n",i);

    if(host_callbacks && *host_callbacks) {
        return (CWaveInfo *)(*host_callbacks)->GetWave(*host_callbacks,i);
    }
    return(&wi);
}
