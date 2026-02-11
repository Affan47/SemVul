operator>>( QDataStream &s, PCXHEADER &ph )
{
  quint8 m, ver, enc, bpp;
  s >> m >> ver >> enc >> bpp;
  ph.Manufacturer = m;
  ph.Version = ver;
  ph.Encoding = enc;
  ph.Bpp = bpp;
  quint16 xmin, ymin, xmax, ymax;
  s >> xmin >> ymin >> xmax >> ymax;
  ph.XMin = xmin;
  ph.YMin = ymin;
  ph.XMax = xmax;
  ph.YMax = ymax;
  quint16 hdpi, ydpi;
  s >> hdpi >> ydpi;
  ph.HDpi = hdpi;
  ph.YDpi = ydpi;
  Palette colorMap;
  quint8 res, np;
  s >> colorMap >> res >> np;
  ph.ColorMap = colorMap;
  ph.Reserved = res;
  ph.NPlanes = np;
  quint16 bytesperline;
  s >> bytesperline; ph.BytesPerLine = bytesperline;
  quint16 paletteinfo;
  s >> paletteinfo; ph.PaletteInfo = paletteinfo;
  quint16 hscreensize, vscreensize;
  s >> hscreensize; ph.HScreenSize = hscreensize;
  s >> vscreensize; ph.VScreenSize = vscreensize;


  quint8 byte;
  while ( s.device()->pos() < 128 )
    s >> byte;

  return s;
}
