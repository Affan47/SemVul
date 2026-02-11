readPacket()
{
    Locker locker(m_Mutex);
    AVStreamPacket* p = new AVStreamPacket();
    AVPacket& pkt = p->GetAVPacket();
    AVM_WRITE("FF reader", 5, "readPacket()\n");
    if (av_read_frame(m_pContext, &pkt) < 0)
    {
        p->Release();
	if (m_pContext->pb && m_pContext->pb->error)
	    AVM_WRITE("FF reader", "error seen\n");


	return -1;
    }


    p->UpdateMembers();

    if ((size_t)pkt.stream_index >= m_Streams.size()) {
	AVM_WRITE("FF reader", "new stream??  i:%d  n:%d  sz:%" PRIsz "\n",
		  pkt.stream_index, m_pContext->nb_streams, m_Streams.size());
        p->Release();
	return 0;
    }

    FFReadStream& s = *m_Streams[pkt.stream_index];
    AVStream& ast = *m_pContext->streams[pkt.stream_index];

    p->SetPos(s.m_uiPosition);
    p->SetTimestamp(((pkt.pts != (int64_t)AV_NOPTS_VALUE) ? pkt.pts : pkt.dts)
		    * AV_TIME_BASE * ast.time_base.num / ast.time_base.den - s.GetStartTime());
    if (pkt.flags & AV_PKT_FLAG_KEY)
	p->SetFlags(p->GetFlags() | KEYFRAME);

    if (p->GetTimestamp() < 0)
        p->SetTimestamp(0);


    switch (ast.codec->codec_type)
    {
    case AVMEDIA_TYPE_AUDIO:
	s.m_uiPosition += pkt.size;
	break;
    case AVMEDIA_TYPE_VIDEO:
    default:
	s.m_uiPosition++;
	break;
    }
#if 0
    printf("---ReadPacket i:%d	 sz:%d	 pts:%" PRId64 "  size:%d   (%" PRId64 ",  %d)\n",
	   pkt.stream_index, s.m_Packets.size(), pkt.pts, pkt.size, p->timestamp, pkt.flags);
#endif

    if (s.m_Packets.size() >= s.m_Packets.capacity() - 1)
    {
	if (1)
	    AVM_WRITE("FF reader", "got too many packets in the queue %d??? (%" PRIsz ", %" PRIsz ")\n",
		      pkt.stream_index, s.m_Packets.size(), s.m_Packets.capacity());
	s.m_Packets.front()->Release();
	s.m_Packets.pop();
    }

    s.m_Packets.push(p);
    return 0;
}
