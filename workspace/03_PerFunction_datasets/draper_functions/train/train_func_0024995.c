AdjustIO(IO_MODE IM, const char* model)
{
    IOMode.bStatus=IM.bStatus && IOMode.bStatus;
    IOMode.bDevID =IM.bDevID  && IOMode.bDevID;

    if (model)
        strncpy(strModel,model, sizeof(strModel));
}
