CloseSndFile(sound_file_format input, FILE * musicin)
{
    (void) input;
    if (fclose(musicin) != 0) {
        if (silent < 10) {
            error_printf("Could not close audio input file\n");
        }
        exit(2);
    }
}
