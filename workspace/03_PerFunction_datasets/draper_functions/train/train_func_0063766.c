startProvidingService()
{
    OFCondition result;
    const char *filename;

    int errors = 0;

    parseCommandLine();

    OFListIterator(MdfJob) job_it;
    OFListIterator(MdfJob) job_last = jobs->end();;
    OFListIterator(OFString) file_it = files->begin();
    OFListIterator(OFString) file_last = files->end();;

    while (file_it != file_last)
    {
        filename = (*file_it).c_str();
        result = loadFile(filename);

        if (result.good())
        {

            job_it = jobs->begin();

            while (job_it != job_last)
            {
                errors += executeJob(*job_it, filename);
                job_it++;
            }

            if (errors == 0 || ignore_errors_option)
            {
                result = ds_man->saveFile(filename, output_xfer_option,
                                          enctype_option, glenc_option,
                                          padenc_option, filepad_option,
                                          itempad_option, output_dataset_option);
                if (result.bad())
                {
                    OFLOG_ERROR(dcmodifyLogger, "couldn't save file: " << result.text());
                    errors++;
                    if (!no_backup_option)
                    {
                        result = restoreFile(filename);
                        if (result.bad())
                        {
                            OFLOG_ERROR(dcmodifyLogger, "couldn't restore file: " << result.text());
                            errors++;
                        }
                    }
                }
            }

            else if (!no_backup_option)
            {
                result = restoreFile(filename);
                if (result.bad())
                {
                    OFLOG_ERROR(dcmodifyLogger, "couldn't restore file!");
                    errors++;
                }
            }
        }

        else
        {
            errors++;
            OFLOG_ERROR(dcmodifyLogger, "unable to load file " << filename <<": " << result.text());
        }
        file_it++;

        if ((file_it != file_last) || (errors > 0))
          OFLOG_INFO(dcmodifyLogger, "------------------------------------");
    }
    return errors;
}
