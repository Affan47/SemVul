set_pre_task(Task *task,IntSet pred,int mt_num,int mtno){

    int  i,count=0;

    for(i=1;i<=mt_num;i++){
        if(in_IntSet(pred,i)){
            task->PreTask[mtno][count] = task->MT_No_inv[i];
            count++;
        }
    }
    return(count);
}
