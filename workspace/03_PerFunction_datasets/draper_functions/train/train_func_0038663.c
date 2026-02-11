writeFloat(float val)
{
#if 1
    gchar *buf = g_strdup_printf("%8.3f", val);
    if (buf) {
        writeString(buf);
        g_free(buf);
    }
#else
    std::string tmp = ftos(val, 'g', 8, 3, 0);
    writeStdString(tmp);
#endif
    return *this;
}
