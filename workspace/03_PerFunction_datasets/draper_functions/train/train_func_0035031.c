unserialize(uint8_t const * ptr)
{
   value_ = *(uint64_t*)(ptr);
   uint32_t viLen;
   scriptSize_ = (uint32_t)BtcUtils::readVarInt(ptr+8, &viLen);
   pkScript_.copyFrom(ptr+8+viLen, scriptSize_);
   nBytes_ = 8 + viLen + scriptSize_;
   scriptType_ = BtcUtils::getTxOutScriptType(pkScript_.getRef());
   recipientBinAddr20_ = BtcUtils::getTxOutRecipientAddr(pkScript_,
                                                         scriptType_);
}
