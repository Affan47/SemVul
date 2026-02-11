trimPath(int n)
{
    int i;
    pathSize = pathSize - n;

    if (pathSize < 2)
        pathSize = 2;

    path = ax25Path[0] + ">";

    for (i = 1; i < pathSize; i++){
        path = path + ax25Path[i];
        if (i < (pathSize-1))
            path = path + ',';
    }

    replace(0,dataIdx-1,path);
    dataIdx = path.length() + 1;
}
