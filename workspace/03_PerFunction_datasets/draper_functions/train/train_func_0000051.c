ReadGifComment(GifComment, MemGif2)
GIFCOMMENT *GifComment;
BYTE       **MemGif2;
{


    if (!(GifComment->CommentData = ReadDataSubBlocks(MemGif2 , &(GifComment->DataSize))))
        return(1);

    GifComment->Terminator = 0;

    return(0);
}
