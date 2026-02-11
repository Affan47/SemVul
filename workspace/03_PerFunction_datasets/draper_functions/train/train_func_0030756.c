arraySizeString() const
{
    QString arraySize = "[";
    if (siz0 != -1) {
	arraySize += QString::number(siz0);
	if (order > 1) arraySize += "," + QString::number(siz1);
	if (order > 2) arraySize += "," + QString::number(siz2);
	if (order > 3) arraySize += "," + QString::number(siz3);
	if (order > 4) arraySize += "," + QString::number(siz4);
    }

    arraySize += "]";
    return arraySize;
}
