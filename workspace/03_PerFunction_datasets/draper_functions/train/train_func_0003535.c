extension() const
    {
        Thumbnail::AutoPtr thumbnail = Thumbnail::create(exifData_);
        if (thumbnail.get() == 0) return "";
        return thumbnail->extension();
    }
