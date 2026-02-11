close()
    {
        int rc = 0;
        if (munmap() != 0) rc = 2;
        if (p_->fp_ != 0) {
            if (std::fclose(p_->fp_) != 0) rc |= 1;
            p_->fp_= 0;
        }
        return rc;
    }
