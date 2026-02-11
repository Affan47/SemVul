sendmessage(){
    QString ms=sender;
    ms.append(": ");
    string sendto;
    sendToEncrypt send;

   ms.append(getmessage());

   sendto=ms.toStdString();

   send.sendToEncrypter(sendto);

   updateconvo(ms);

}
