tipsImg() const
{
    if (MainModel::self()->isHorizontal() || mTipsImgVertical == "")
        return mTipsImg;
    else
        return mTipsImgVertical;
}
