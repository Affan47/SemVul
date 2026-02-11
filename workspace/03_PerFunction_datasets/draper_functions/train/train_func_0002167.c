broadcast( SP_Response * response, const char * buffer, SP_Sid_t * ignoreSid )
{
	if( mOnlineSidList->getCount() > 0 ) {
		SP_Message * msg = new SP_Message();
		mOnlineSidList->copy( msg->getToList(), ignoreSid );
		msg->setCompletionKey( ++mMsgSeq );

		msg->getMsg()->append( buffer );
		response->addMessage( msg );
	}
}
