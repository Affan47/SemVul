detect_post_charset(){
	if(is_post && !is_post_charset_detected){
		fpost_charset=detect_charset(frequest_info.content_type);
		is_post_charset_detected=true;
	}
}
