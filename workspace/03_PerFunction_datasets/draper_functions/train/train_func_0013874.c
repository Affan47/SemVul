setPublicKeyAsDOMNode(DOMNode* node)
	{
		DOMNode* root=node;
		while(root!=NULL)
			{
				if(equals(root->getNodeName(),"RSAKeyValue"))
					{
						RSA* tmpRSA=RSA_new();
						UINT32 decLen=4096;
						UINT8 decBuff[4096];
						DOMNode* child=root->getFirstChild();
						while(child!=NULL)
							{
								if(equals(child->getNodeName(),"Modulus"))
									{
										if(tmpRSA->n!=NULL)
											BN_free(tmpRSA->n);
										UINT8* tmpStr=new UINT8[4096];
										UINT32 tmpStrLen=4096;
										getDOMElementValue(child,tmpStr,&tmpStrLen);
										decLen=4096;
										CABase64::decode(tmpStr,tmpStrLen,decBuff,&decLen);
										delete []tmpStr;
										tmpStr = NULL;
										tmpRSA->n=BN_bin2bn(decBuff,decLen,NULL);
									}
								else if(equals(child->getNodeName(),"Exponent"))
									{
										if(tmpRSA->e!=NULL)
											BN_free(tmpRSA->e);
										UINT8* tmpStr=new UINT8[4096];
										UINT32 tmpStrLen=4096;
										getDOMElementValue(child,tmpStr,&tmpStrLen);
										decLen=4096;
										CABase64::decode(tmpStr,tmpStrLen,decBuff,&decLen);
										delete []tmpStr;
										tmpStr = NULL;
										tmpRSA->e=BN_bin2bn(decBuff,decLen,NULL);
									}
								child=child->getNextSibling();
							}
						if(tmpRSA->n!=NULL&&tmpRSA->e!=NULL)
							{
								if(m_pRSA!=NULL)
									RSA_free(m_pRSA);
								m_pRSA=tmpRSA;
								setRSAFlags(m_pRSA);
								return E_SUCCESS;
							}
						RSA_free(tmpRSA);
						return E_UNKNOWN;
					}
				root=root->getNextSibling();
			}
		return E_UNKNOWN;
	}
