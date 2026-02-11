isExpired(qint64 currentDate) const
{
    if (currentDate == -1)
        currentDate = epoch();

    return (mExpireDate != 0) && (mExpireDate < currentDate);
}
