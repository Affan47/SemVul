ajListstrIterTrace(const AjIList iter)
{
    if(!iter)
        return;

    ajDebug("\nIterator Head %p ReadHead %p Here %p Back %B Item %S\n",
            iter->Head, iter->ReadHead, iter->Here,iter->Back,
            (AjPStr)iter->Here->Item);

    return;
}
