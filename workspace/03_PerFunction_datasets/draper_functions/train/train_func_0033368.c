setOption(const QByteArray &opt, const QByteArray &value)
{
   if (isQt)
   {

      QByteArray argString = "-";
      argString += opt;
      if (opt == "qmljsdebugger") {


          addArgument(argString + "=" + value);
      } else {
          addArgument(argString);
          addArgument(value);
      }

#if defined(Q_WS_X11) || defined(Q_WS_QWS)

      if (argString == "-display")
      {
         setenv(DISPLAY, value.data(), true);
      }
#endif
   }
   if (!parsedOptionList) {
      parsedOptionList = new KCmdLineParsedOptions;
   }

   parsedOptionList->insertMulti( opt, value );
}
