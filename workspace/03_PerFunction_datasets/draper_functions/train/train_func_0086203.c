reset_last_acks(int i){
    for(int j=ACKBACK-1;j>=0;j--)
        lastacks[i][j]=0;
    lastackPos[i]=0;
    highest_ack[i]=0;
}
