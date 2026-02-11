reset() {
    if (hdfs_)
    {
#ifdef HDFS

        jmethodID resetMethod = env_->GetMethodID(cls_, "reset", "()V");
        if (resetMethod == 0) {
            GM_JNI_Handler::getInstance()->printAndClearException();
            fprintf (stderr, "JNI Error: Cannot get reset method in HDFSReader\n");
            failed_ = true;
            return;
        }


        env_->CallVoidMethod(readerObj_, resetMethod);
#endif
    }
    else {
        fs_.clear();
        fs_.seekg(0, std::ios::beg);
        if (fs_.fail()) {
            fprintf (stderr, "Error moving file pointer to the beginning of file %s\n", filename_.c_str());
        }
    }
}
