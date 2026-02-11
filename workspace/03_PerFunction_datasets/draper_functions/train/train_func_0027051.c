Update()
{

  mwxConfig->Write(_T("Windowed"), mWindowedValue);
  mwxConfig->Write(_T("True Color"), mTrueColorValue);
  mwxConfig->Write(_T("Sound"), mSoundValue);
  mwxConfig->Write(_T("Joystick"), mJoystickValue);
  mwxConfig->Write(_T("Debug"), mDebugValue);
  mwxConfig->Write(_T("v1.07"), mV107Value);
  mwxConfig->Write(_T("Show Introduction"), mShowIntroductionText);
  mwxConfig->Write(_T("Warn on Edit"), mWarnOnEdit);


  mwxConfig->Write(_T("Write Ini"), mWriteIniValue);
  mwxConfig->Write(_T("Show Developer Buttons"), mShowDeveloperButtons);
  mwxConfig->Write(_T("Close DFArc on Play"), mCloseDfarcOnPlay);
  mwxConfig->Write(_T("Override Dink Directory"), mOverrideDinkrefDir);
  mwxConfig->Write(_T("Specified Dink Directory"), mSpecifiedDinkrefDir);
  mwxConfig->Write(_T("Additional D-Mods Directory"), mDModDir);
  mwxConfig->Write(_T("Dink Executable"), mDinkExe);
  mwxConfig->Write(_T("Editor Executable"), mEditorExe);
  mwxConfig->Write(_T("Language"), mForceLocale);

  mwxConfig->Write(_T("Last Selected D-Mod"), mSelectedDmod);
  return;
}
