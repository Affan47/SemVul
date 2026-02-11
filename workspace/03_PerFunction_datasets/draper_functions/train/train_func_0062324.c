Write(trpgWriteBuffer &buf)
{

    if (!isValid())
        return false;

    buf.Begin(TRPGHEADER);
    buf.Add((int32)verMajor);
    buf.Add((int32)verMinor);
    buf.Add((int32)dbVerMajor);
    buf.Add((int32)dbVerMinor);
    buf.Add(origin);
    buf.Add(sw);
    buf.Add(ne);
    buf.Add((uint8)tileType);

    buf.Add((int32)numLods);

    buf.Begin(TRPGHEAD_LODINFO);
    for (int i=0;i<numLods;i++) {
        buf.Add(lodSizes[i]);
        buf.Add(lodRanges[i]);
        buf.Add(tileSize[i]);
    }
    buf.End();

    buf.Add(maxGroupID);

    if((verMajor >= TRPG_NOMERGE_VERSION_MAJOR) && (verMinor >=TRPG_NOMERGE_VERSION_MINOR)) {
        buf.Add(flags);
        buf.Add(rows);
        buf.Add(cols);
    }

    buf.End();

    return true;
}
