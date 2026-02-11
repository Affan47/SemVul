execute()
{
  (*__inputMesh).execute();
  ffout(3) << "Converting to tetrahedra "
	   << (*__inputMesh) << '\n';
  MeshTetrahedrizor mt((*__inputMesh).mesh());

  mt.run();

  __mesh = mt.mesh();
  ffout(3) << "Converting to tetrahedra done\n";
}
