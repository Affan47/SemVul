generateReturnObjectPath()
{
    static int number = 1;

    return "/org/kde/solid/HalStorageAccess_"+QString::number(number++);
}
