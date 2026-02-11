startElement (const QString & ,
			     const QString & localName, const QString & qName,
			     const QXmlAttributes & atts )
  {
    if (localName == "wpt") {
      currentWpt = GpxWaypoint();
      double lat = atts.value("lat").toDouble();;
      double lon = atts.value("lon").toDouble();;
      currentWpt.setLocation(LatLng(lat, lon));
      stateStack << state;
      state = e_wpt;
    }

    else if (localName == "trk") {
      stateStack << state;
      state = e_trk;
      currentTrk.clear();
    }

    else if (localName == "trkseg") {
      stateStack << state;
      state = e_trkseg;
      currentTrkSeg.clear();
    }

    else if (localName == "trkpt") {
      currentTrkPt = GpxTrackPoint();
      double lat = atts.value("lat").toDouble();;
      double lon = atts.value("lon").toDouble();;
      currentTrkPt.setLocation(LatLng(lat, lon));
      stateStack << state;
      state = e_trkpt;
    }

    else if (localName == "rte") {
      stateStack << state;
      state = e_rte;
      currentRte.clear();
    }

    else if (localName == "rtept") {
      currentRtePt = GpxRoutePoint();
      double lat = atts.value("lat").toDouble();;
      double lon = atts.value("lon").toDouble();;
      currentRtePt.setLocation(LatLng(lat, lon));
      stateStack << state;
      state = e_rtept;
    }


    else if (state == e_wpt ||
	     state == e_trkpt || state == e_trkseg || state == e_trk ||
	     state == e_rte || state == e_rtept) {
    }
    else {


    }
    return true;
  }
