prevOnLineExists()
{
    if (!parent())
        return false;

    if (prevOnLine())
        return true;

    return parent()->prevOnLineExists();
}
