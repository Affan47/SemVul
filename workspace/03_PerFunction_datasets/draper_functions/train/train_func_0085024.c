xaccTransRetDateDueTS (const Transaction *trans)
{
    Timespec ts = {0, 0};
    if (trans) xaccTransGetDateDueTS (trans, &ts);
    return ts;
}
