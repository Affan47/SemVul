loadFriends(){
    QList<QStringList> list;
    QStringList templist;
    QStringList onlinefriends;
    QList<QStringList> offlist;
    QStringList offtemplist;
    QStringList offlinefriends;


    onlinefriends=(getusers());
    templist=onlinefriends;
    list.append(templist);


    offlinefriends=(getOffline());
    offtemplist=offlinefriends;
    offlist.append(offtemplist);


    QString temper;
    int i=0;

    foreach(temper, list[i]){

    ui->listoffriends->insertItem(i,temper);
    i++;
    }

    QString offtemper;
    int j=0;

    foreach(offtemper, offlist[j]){

    ui->offlinelist->insertItem(j,offtemper);
    j++;
    }


}
