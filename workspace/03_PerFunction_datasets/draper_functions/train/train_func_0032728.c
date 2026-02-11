TransferParameters( Shuttle & shuttle )
{
   shuttle.TransferDouble( wxT("Threshold"), mThresholdDB, -12.0f );
   shuttle.TransferDouble( wxT("NoiseFloor"), mNoiseFloorDB, -40.0f );
   shuttle.TransferDouble( wxT("Ratio"), mRatio, 2.0f );
   shuttle.TransferDouble( wxT("AttackTime"), mAttackTime, 0.2f );
   shuttle.TransferDouble( wxT("DecayTime"), mDecayTime, 1.0f );
   shuttle.TransferBool( wxT("Normalize"), mNormalize, true );
   shuttle.TransferBool( wxT("UsePeak"), mUsePeak, false );
   return true;
}
