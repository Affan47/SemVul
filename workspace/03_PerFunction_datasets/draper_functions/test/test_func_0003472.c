description(char* buf, int buflen) {
    char vers[256], cuda_vers[256];
    if (display_driver_version) {
#ifdef __APPLE__
     	int maj = display_driver_version >> 16;
    	int min = (display_driver_version >> 8) & 0xff;
    	int rev = display_driver_version & 0xff;
        sprintf(vers, "%d.%d.%d", maj, min, rev);
#else
        int maj = display_driver_version/100;
        int min = display_driver_version%100;
        sprintf(vers, "%d.%02d", maj, min);
#endif
    } else {
        strcpy(vers, "unknown");
    }
    if (cuda_version) {
        int maj = cuda_version/1000;
        int min = (cuda_version%1000)/10;
        sprintf(cuda_vers, "%d.%d", maj, min);
    } else {
        strcpy(cuda_vers, "unknown");
    }
    snprintf(buf, buflen,
        "%s (driver version %s, CUDA version %s, compute capability %d.%d, %.0fMB, %.0fMB available, %.0f GFLOPS peak)",
        prop.name, vers, cuda_vers, prop.major, prop.minor,
        prop.totalGlobalMem/MEGA, available_ram/MEGA, peak_flops/1e9
    );
}
