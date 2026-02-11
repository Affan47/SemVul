scriptlevel(const MmlNode *child) const
{
    int sl = MmlNode::scriptlevel();

    MmlNode *i = index();
    if (child != 0 && child == i)
	return sl + 1;
    else
	return sl;
}
