abortproc(void)
{
    log("Terminating all instances... [%u]\n",instanceList.size());
    for(std::list<PseuInstanceRunnable*>::iterator i=instanceList.begin();i!=instanceList.end();i++)
    {
        (*i)->GetInstance()->SetFastQuit(true);
        (*i)->GetInstance()->Stop();
    }
}
