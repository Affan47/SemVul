escape(string value)
		{
			strreplace(value, '&', "&amp;");
			strreplace(value, '<', "&lt;");
			strreplace(value, '>', "&gt;");
			strreplace(value, '"', "&quot;");
			strreplace(value, '\'', "&#39;");
			return value;
		}
