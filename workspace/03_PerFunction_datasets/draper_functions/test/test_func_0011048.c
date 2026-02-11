FilePlayBack(ClientInfo *p)
{
   int TotalDelta = 0;
   int ThisDelta;
   int NewDelay;
   int Packets2Send = 0;
   ClientFileIO *pFIO = (ClientFileIO *) p->p;
   ConfClient *pCC = pFIO->pCC;

   if(pFIO->TimeFirstTx.tv_sec != 0) {
      TotalDelta = ((TimeNow.tv_sec - pFIO->TimeFirstTx.tv_sec) * 1000) +
                   ((TimeNow.tv_usec - pFIO->TimeFirstTx.tv_usec) / 1000);


      Packets2Send = (TotalDelta / 80) - pFIO->x;


      ThisDelta = ((TimeNow.tv_sec - pFIO->TimeLastTx.tv_sec) * 1000) +
                  ((TimeNow.tv_usec - pFIO->TimeLastTx.tv_usec) / 1000);

      D3PRINTF(("FilePlayBack(): Last delta %d milliseconds.\n",ThisDelta));

      pFIO->Timeout -= ((ThisDelta - 80)/2);
      if(pFIO->Timeout <= 0) {

         pFIO->Timeout = 1;
         if(!pFIO->bTooSlowLogged) {
            pFIO->bTooSlowLogged = TRUE;
            LOG_ERROR(("FilePlayBack(): Desired timeout reached zero after %d"
                       " packets.\n",pFIO->x));
         }
      }
   }
   else {

      Packets2Send = 1;
      pFIO->TimeFirstTx = TimeNow;
   }

   if(Packets2Send <= 0) {
      Packets2Send = 0;
      NewDelay = ((pFIO->x + 1) * 80) - TotalDelta;
      if(NewDelay <= 0) {

         NewDelay = 1;
      }

      D3PRINTF(("FilePlayBack(): Too soon to send, waiting %d milliseconds.\n",
                NewDelay));
      SetTimeout(p,NewDelay);
   }
   else {
      D3PRINTF(("FilePlayBack(): Send %d packets this time.\n",Packets2Send));
      if(!SendAudioFromFile(p,pFIO,Packets2Send)) {
         PlayBackComplete(pCC,"playback complete");
      }
   }

   return FALSE;
}
