getNext()
   {

      if (mTokenStack.size() != 0)
      {

         Token tok;
         mCurToken = mTokenStack.top();
         mTokenStack.pop();

         return;
      }

      bool finished = false;

      std::string generic;


      char c;

      do
      {
         if (mPutbackChar == char(-1))
         {
            c = mInput.get();
            mLocation.step();
         }
         else
         {
            c = mPutbackChar;
            mPutbackChar = char(-1);
            mLocation.step();
         }


         if (c == char(EOF))
         {
            if (generic.length() != 0)
            {
               mCurToken = c;
               return;
            }
            else
            {
               break;
            }
         }


         if (isLiteral(c))
         {
            mCdataMode = false;
            if (generic.length() == 0)
            {
               mCurToken = c;


               if (c == '>')
               {
                  mCdataMode = true;
               }

               return;
            }
            mPutbackChar = c;
            mLocation.step(-1);
            break;
         }


         if (isStringDelimiter(c) && !mCdataMode)
         {
            generic = c;
            char delim = c;
            do
            {
               c = mInput.get();
               mLocation.step();
               if (c == char(EOF))
               {
                  break;
               }
               generic += c;
            }
            while (c != delim);
            break;
         }


         if (isWhiteSpace(c))
         {
            if (generic.length() == 0)
            {
               continue;
            }
            else
            {
               if (!mCdataMode)
               {
                  break;
               }
            }
         }


         if (isNewLine(c) )
         {
            if (!mCdataMode || generic.length() == 0)
            {
               continue;
            }
         }


         generic += c;
      }
      while (!finished);


      mCurToken = generic;
   }
