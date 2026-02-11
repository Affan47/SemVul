each_function_pattern_pixel(int *x,int *y)
    {
        if(this->each_finder_pattern_pixel(x,y))
            return(this);
        if(this->each_timing_pattern_pixel(x,y))
            return(this);
        if(this->each_alignment_pattern_pixel(x,y))
            return(this);
        if(this->each_version_pattern_pixel(x,y))
            return(this);
        return(this->each_formatinfo_pattern_pixel(x,y));
    }
