rtl871x_open_fw(struct _adapter *padapter, const u8 **ppmappedfw)
{
	const struct firmware **praw = &padapter->fw;

	if (padapter->fw->size > 200000) {
		dev_err(&padapter->pnetdev->dev, "r8172u: Badfw->size of %d\n",
			(int)padapter->fw->size);
		return 0;
	}
	*ppmappedfw = (*praw)->data;
	return (*praw)->size;
}
