_Cnd_OutDebug( const char* FormattedMsg, const char* StrTitle, const char* File, int32_t Line, int32_t Title, const char* Mes2, int32_t fatal ){
	#ifdef __WINDOWS_H

 			MessageBox(NULL, FormattedMsg, StrTitle, (fatal==1 ? MB_ICONSTOP:MB_ICONEXCLAMATION) | MB_OK | MB_TASKMODAL);
	#else
			printf("%s\n",FormattedMsg);
	#endif

	#if defined(_CND_DEBUG_WARN_DEBUGGER)
			OutputDebugString(FormattedMsg);
			DebugBreak();
	#endif

	if ( fatal )
		debugFatalExit(1);
}
