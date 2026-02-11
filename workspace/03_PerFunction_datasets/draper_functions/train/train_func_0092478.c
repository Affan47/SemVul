SendByte(unsigned tx_byte)
{
#ifdef HAVE_TXFIFO
    Dprintf (( "SendByte <%02X> : head=%d, tail=%d, txreg=%p\n",
               tx_byte, m_FifoHead, m_FifoTail, m_txreg ))
    if ( m_FifoHead != m_FifoTail || !m_txreg || !m_txreg->is_empty() )
    {
        int newHead;

        m_TxFIFO[m_FifoHead] = tx_byte;
        newHead = m_FifoHead+1;
        if ( newHead >= m_FifoLen )
            newHead = 0;
        if ( newHead == m_FifoTail )
        {
            int newLen = m_FifoLen + 32;
            unsigned char * newFIFO;
            newFIFO = new unsigned char[newLen];
            int oldTail = m_FifoTail;
            int dIdx = 0;
            int sIdx;
            for ( sIdx = oldTail; sIdx < m_FifoLen; )
                newFIFO[dIdx++] = m_TxFIFO[sIdx++];
            for ( sIdx = 0; sIdx < newHead; )
                newFIFO[dIdx++] = m_TxFIFO[sIdx++];
            unsigned char * oldFIFO = m_TxFIFO;
            m_TxFIFO = newFIFO;
            m_FifoTail -= oldTail;
            m_FifoHead = dIdx;
            m_FifoLen = newLen;
            delete oldFIFO;
        }
        else
            m_FifoHead = newHead;

    }
    else
#endif
        if (m_txreg)
            m_txreg->mSendByte(tx_byte);
}
