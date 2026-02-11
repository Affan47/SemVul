chopBypass(String url, bool infectionbypass)
{
	if (url.contains(infectionbypass ? "GIBYPASS=" : "GBYPASS=")) {
		if (url.contains(infectionbypass ? "?GIBYPASS=" : "?GBYPASS=")) {
			String bypass(url.after(infectionbypass ? "?GIBYPASS=" : "?GBYPASS="));
			header.front() = header.front().before(infectionbypass ? "?GIBYPASS=" : "?GBYPASS=") + header.front().after(bypass.toCharArray());
		} else {
			String bypass(url.after(infectionbypass ? "&GIBYPASS=" : "&GBYPASS="));
			header.front() = header.front().before(infectionbypass ? "&GIBYPASS=" : "&GBYPASS=") + header.front().after(bypass.toCharArray());
		}
	}
	cachedurl = "";
}
