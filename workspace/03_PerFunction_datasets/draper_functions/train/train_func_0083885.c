webwin_ehandler(enum mg_event event,
                           struct mg_connection *conn) {

	const struct mg_request_info *request_info = mg_get_request_info(conn);

	if (event != MG_NEW_REQUEST) {
		return NULL;
	}
#ifdef DEBUG
	printf("Got event with uri = '%s'\n",request_info->uri);
#endif
	if (strcmp(request_info->uri, "/ajax/messages") == 0) {
		ajax_get_messages(conn, request_info);
	} else if (strcmp(request_info->uri, "/webdisp.js") == 0) {
#ifndef NEVER
		char *webdisp_js =
	"\r\n"
	"if (typeof XMLHttpRequest == \"undefined\") {\r\n"
	"	XMLHttpRequest = function () {\r\n"
	"		try { return new ActiveXObject(\"Msxml2.XMLHTTP.6.0\"); }\r\n"
	"			catch (e) {}\r\n"
	"		try { return new ActiveXObject(\"Msxml2.XMLHTTP.3.0\"); }\r\n"
	"			catch (e) {}\r\n"
	"		try { return new ActiveXObject(\"Microsoft.XMLHTTP\"); }\r\n"
	"			catch (e) {}\r\n"
	"		throw new Error(\"This browser does not support XMLHttpRequest.\");\r\n"
	"	};\r\n"
	"}\r\n"
	"\r\n"
	"var ccolor = \"\";\r\n"
	"var oXHR;\r\n"
	"\r\n"
	"function XHR_response() {\r\n"
	"	if (oXHR.readyState != 4)\r\n"
	"		return;\r\n"
	"\r\n"
	"	if (oXHR.status != 200) {\r\n"
	"		return;\r\n"
	"	}\r\n"
	"	var rt = oXHR.responseText;\r\n"
	"	if (rt.charAt(0) == '\\r' && rt.charAt(1) == '\\n')\r\n"
	"		rt = rt.slice(2);\r\n"
	"	if (ccolor != rt) {\r\n"
	"		ccolor = rt;\r\n"
	"		document.body.style.background = ccolor;\r\n"
	"	}\r\n"
	"	oXHR.open(\"GET\", \"/ajax/messages?\" + document.body.style.background + \" \" + Math.random(), true);\r\n"
	"	oXHR.onreadystatechange = XHR_response;\r\n"
	"	oXHR.send();\r\n"
	"}\r\n"
	"\r\n"
	"window.onload = function() {\r\n"
	"	ccolor = \"#808080\";\r\n"
	"	document.body.style.background = ccolor;\r\n"
	"\r\n"
	"	oXHR = new XMLHttpRequest();\r\n"
	"	oXHR.open(\"GET\", \"/ajax/messages?\" + document.body.style.background, true);\r\n"
	"	oXHR.onreadystatechange = XHR_response;\r\n"
	"	oXHR.send();\r\n"
	"};\r\n";
	    mg_write(conn, webdisp_js, strlen(webdisp_js));
#else
		return NULL;
#endif
	} else {
	    mg_printf(conn, "HTTP/1.1 200 OK\r\n"
		"Cache-Control: no-cache\r\n"
		"Content-Type: text/html\r\n\r\n"
		"<html>\r\n"
		"<head>\r\n"
		"<title>ArgyllCMS Web Display</title>\r\n"
		"<script src=\"webdisp.js\"></script>\r\n"
		"</head>\r\n"
		"</html>\r\n"
		);
	}


	return "yes";
}
