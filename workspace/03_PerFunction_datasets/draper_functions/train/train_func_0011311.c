strip(TagTypes tags)
{
  if(tags & ID3v2)
    removeChunk(d->tagChunkID);

  if(tags & Info){
    TagLib::uint chunkId = findInfoTagChunk();
    if(chunkId != TagLib::uint(-1))
      removeChunk(chunkId);
  }
}
