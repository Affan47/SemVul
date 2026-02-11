writeHeader()
{
    _stream << quint16(0x01da);
    _stream << _rle << _bpc << _dim;
    _stream << _xsize << _ysize << _zsize;
    _stream << _pixmin << _pixmax;
    _stream << quint32(0);

    for (int i = 0; i < 80; i++)
        _imagename[i] = '\0';
    _stream.writeRawData(_imagename, 80);

    _stream << _colormap;
    for (int i = 0; i < 404; i++)
        _stream << quint8(0);
}
