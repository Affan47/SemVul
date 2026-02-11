HASH_Init(HASH_InitTypeDef* HASH_InitStruct)
{

  assert_param(IS_HASH_ALGOSELECTION(HASH_InitStruct->HASH_AlgoSelection));
  assert_param(IS_HASH_DATATYPE(HASH_InitStruct->HASH_DataType));
  assert_param(IS_HASH_ALGOMODE(HASH_InitStruct->HASH_AlgoMode));


  HASH->CR &= ~ (HASH_CR_ALGO | HASH_CR_DATATYPE | HASH_CR_MODE);
  HASH->CR |= (HASH_InitStruct->HASH_AlgoSelection | \
               HASH_InitStruct->HASH_DataType | \
               HASH_InitStruct->HASH_AlgoMode);


  if(HASH_InitStruct->HASH_AlgoMode == HASH_AlgoMode_HMAC)
  {
    assert_param(IS_HASH_HMAC_KEYTYPE(HASH_InitStruct->HASH_HMACKeyType));
    HASH->CR &= ~HASH_CR_LKEY;
    HASH->CR |= HASH_InitStruct->HASH_HMACKeyType;
  }


  HASH->CR |= HASH_CR_INIT;
}
