read(QvInput *in, QvNode *&node)
{
    QvBool ret;

    ret = QvNode::read(in, node);

    if (ret && node == NULL && ! in->eof()) {
	char	c;
	in->get(c);
	QvReadError::post(in, "Extra characters ('%c') found in input", c);
	ret = FALSE;
    }

    return ret;
}
