eqGlobalList()
{


    QStringList mGlobalList;
    mGlobalList += eqDefaultPresetsList();
    mGlobalList += eqUserList();
    return mGlobalList;
}
