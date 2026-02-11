isPower(vector<bool> const &mask,
			     vector<bool> const &isfixed) const
{
    unsigned int nmask = 0;
    for (unsigned int i = 0; i < mask.size(); ++i) {
	nmask += mask[i];
    }

    if (nmask > 1)
	return false;
    else
	return isScale(mask, vector<bool>());

}
