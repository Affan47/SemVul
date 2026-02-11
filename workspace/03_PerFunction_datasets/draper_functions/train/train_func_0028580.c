AdpcmTx()
{
   adpcm_coder(TxAudioBuf,Adpcm.Buf,AUDIO_SAMPLES_PER_ADPCM_PACKET,&TxADPCM);

   if(mCC->Proto == PROTO_SF) {

      soundbuf *pSFHdr = (soundbuf *) &Adpcm.Buf[-SIZEOF_SOUNDBUF];
      u_int8 *pData = (u_int8 *) Adpcm.Buf;
      u_int8 *sp = (u_int8 *) &pData[ADPCM_PACKET_DATA_BYTES];
      int TxLen = SIZEOF_SOUNDBUF + ADPCM_PACKET_DATA_BYTES + 3;

      pSFHdr->compression = (int) htonl(fCompADPCM| fProtocol);
      pSFHdr->buffer.buffer_len = (int) htonl(ADPCM_PACKET_DATA_BYTES+3);
      memset(pSFHdr->sendinghost,0,sizeof(pSFHdr->sendinghost));
      strncpy(pSFHdr->sendinghost,ConferenceCall,
              sizeof(pSFHdr->sendinghost));
      sp[0] = (u_int8) (((u_int16)TxADPCMStart.valprev) >> 8);
      sp[1] = (TxADPCMStart.valprev & 0xff);
      sp[2] = TxADPCMStart.index;


      SendAudioPacket(pSFHdr,TxLen);
   }
   else if(mCC->Proto == PROTO_RTP) {

      rtp_hdr_t *pRtpHdr = (rtp_hdr_t *) &Adpcm.Buf[-(RTP_HDR_SIZE+4)];
      u_int8 *sp = (u_int8 *) &Adpcm.Buf[-4];
      int TxLen = RTP_HDR_SIZE + ADPCM_PACKET_DATA_BYTES + 4;

      memset(pRtpHdr,0,sizeof(rtp_hdr_t));
      pRtpHdr->pt = RTP_PT_DVI4_8K;
      pRtpHdr->seq = htons(RtpTxSequence++);
      pRtpHdr->ssrc = OurNodeID;
      pRtpHdr->version = 2;
      sp[0] = (u_int8) (((u_int16)TxADPCMStart.valprev) >> 8);
      sp[1] = (TxADPCMStart.valprev & 0xff);
      sp[2] = TxADPCMStart.index;


      SendAudioPacket(pRtpHdr,TxLen);
   }
   else {
      LOG_ERROR(("%s: Error protocol = %d.\n",__FUNCTION__,mCC->Proto));
   }
   TxADPCMStart = TxADPCM;
}
