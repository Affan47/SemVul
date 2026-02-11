GetContentPoint(int off) const
{
    if (off >= readBuff_->curSize_) return NULL;

    return readBuff_->curPtr_ + off;
}
