QueueItem(pkgAcquire::Queue::QItem *Item)
{
   if (OutFd == -1)
      return false;

   string Message = "600 URI Acquire\n";
   Message.reserve(300);
   Message += "URI: " + Item->URI;
   Message += "\nFilename: " + Item->Owner->DestFile;
   Message += Item->Owner->Custom600Headers();
   Message += "\n\n";

   if (Debug == true)
      clog << " -> " << Access << ':' << QuoteString(Message,"\n") << endl;
   OutQueue += Message;
   OutReady = true;

   return true;
}
