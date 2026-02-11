extractDataFromSvn(FILE* EntriesFile, bool url, RawData& data)
{
    char buf[200];

    char repo_str[200];
    char num_str[200];

    fgets(buf,200,EntriesFile);
    fgets(buf,200,EntriesFile);
    fgets(buf,200,EntriesFile);
    fgets(buf,200,EntriesFile); sscanf(buf,"%s",num_str);
    fgets(buf,200,EntriesFile); sscanf(buf,"%s",repo_str);
    fgets(buf,200,EntriesFile);
    fgets(buf,200,EntriesFile);
    fgets(buf,200,EntriesFile);
    fgets(buf,200,EntriesFile);
    fgets(buf,200,EntriesFile); sscanf(buf,"%10sT%8s",data.date_str,data.time_str);

    if(url)
        sprintf(data.rev_str,"%s at %s",num_str,repo_str);
    else
        strcpy(data.rev_str,num_str);
}
