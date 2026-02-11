getTrackFilenames(FXIntList & ids,FXStringList & files,FXLongList & importdates,const FXString & root) {
  FXString dir;
  FXint path;
  FXString filename;
  FXint last_path=-1;
  FXint id,rootid;
  FXlong date;

  FXString query;
  GMQuery list;
  try {
    if (!root.empty()) {
      if (!findPath(root,rootid)) return true;
      list.compile(db,"SELECT tracks.id,tracks.path,tracks.mrl,tracks.importdate FROM tracks, directories WHERE tracks.path == directories.id AND (directories.id == " + GMStringVal(rootid) + " OR directories.path LIKE '%/" + GMStringVal(rootid) +"/%');");
      }
    else {
      list.compile(db,"SELECT id,path,mrl,importdate FROM tracks ORDER BY path");
      }
    while(list.execute()){
      list.getResult(0,id);
      list.getResult(1,path);
      list.getResult(2,filename);
      list.getResult(3,date);
      if (path==-1) {
        files.append(filename);
        ids.append(id);
        importdates.append(date);
        }
      else {
        if (path!=last_path){
          dir = getPathName(path);
          last_path = path;
          }
        if (dir.empty())
          files.append(filename);
        else
          files.append(dir+PATHSEPSTRING+filename);
        ids.append(id);
        importdates.append(date);
        }
      }
    list.reset();
    }
  catch (FXCompileException &){
    list.reset();
    return false;
    }
  catch (FXExecuteException &){
    list.reset();
    return false;
    }
  return true;
  }
