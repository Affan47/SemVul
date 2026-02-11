upgrade_to_2009() {

  if (!db.execute("ALTER TABLE albums RENAME TO albums_old;"))
    return false;

  if (!db.execute(create_albums))
    return false;

  if (!db.execute("INSERT INTO albums (id, name, artist, year) SELECT albums_old.id, name, artist,year FROM albums_old,album_artist,tracks WHERE album_artist.album == albums_old.id AND tracks.album==albums_old.id GROUP BY albums_old.id;"))
    return false;

  if (!db.execute("DROP TABLE albums_old;"))
    return false;

  if (!db.execute("DROP TABLE album_artist;"))
    return false;

  if (!db.execute("ALTER TABLE tracks ADD COLUMN artist INTEGER;"))
    return false;
  if (!db.execute("ALTER TABLE tracks ADD COLUMN replay_gain REAL;"))
    return false;
  if (!db.execute("ALTER TABLE tracks ADD COLUMN replay_peak REAL;"))
    return false;

  if (!db.execute("UPDATE tracks SET artist = ( SELECT DISTINCT(albums.artist) FROM albums WHERE albums.id == tracks.album );"))
    return false;

  GMQuery q;
  q.compile(db,"UPDATE tracks SET replay_gain = ?, replay_peak = ?;");
  FXdouble v=NAN;
  q.setParameter(0,v);
  q.setParameter(1,v);
  q.execute();
  q.reset();


  if (!db.hasTable("streams")) {
    if (!db.execute(create_streams))
      return false;
    }

  if (sqlite3_libversion_number()>=SQVERSION(3,3,0)) {
    db.execute("CREATE INDEX IF NOT EXISTS tracks_album ON tracks(album);");
    db.execute("CREATE INDEX IF NOT EXISTS playlist_tracks_idx ON playlist_tracks(track);");
    }
  else {
    if (!db.hasIndex("tracks_album")) db.execute("CREATE INDEX tracks_album ON tracks(album);");
    if (!db.hasIndex("playlist_tracks_idx")) db.execute("CREATE INDEX playlist_tracks_idx ON playlist_tracks(track);");
    }

  db.setVersion(GOGGLESMM_DATABASE_SCHEMA_VERSION);


  db.execute("VACUUM;");

  return true;
  }
