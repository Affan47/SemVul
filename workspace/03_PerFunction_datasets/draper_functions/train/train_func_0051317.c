load()
    {
        OGRE_LOCK_AUTO_MUTEX;
        if (!mZzipDir)
        {
            zzip_error_t zzipError;
            mZzipDir = zzip_dir_open_ext_io(mName.c_str(), &zzipError, 0, mPluginIo);
            checkZzipError(zzipError, "opening archive");


            ZZIP_DIRENT zzipEntry;
            while (zzip_dir_read(mZzipDir, &zzipEntry))
            {
                FileInfo info;
                info.archive = this;

                StringUtil::splitFilename(zzipEntry.d_name, info.basename, info.path);
                info.filename = zzipEntry.d_name;

                info.compressedSize = static_cast<size_t>(zzipEntry.d_csize);
                info.uncompressedSize = static_cast<size_t>(zzipEntry.st_size);

                if (info.basename.empty())
                {
                    info.filename = info.filename.substr (0, info.filename.length () - 1);
                    StringUtil::splitFilename(info.filename, info.basename, info.path);


                    info.compressedSize = size_t (-1);
                }
                else
                {
                    info.filename = info.basename;
                }
                mFileList.push_back(info);

            }

        }
    }
